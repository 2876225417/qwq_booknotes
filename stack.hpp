#ifndef STACK_HPP_
#define STACK_HPP_


#include <cstdarg>
#include <stdexcept>
#include <vector>
#include "item.hpp"


#include <exception>

namespace qwq_stack {


    class stack_exception: public std::exception {
        
    };

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
        if (!elems.empty()) 
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
        if (!elems.empty())
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
            return num_elems == MAXSIZE ? true : false;
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
            throw std::out_of_range("sized_stack<T>::empty(): empty stack!");
        
    }




}
#endif // STACK_HPP_