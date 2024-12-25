

## 关于 `typename`关键字的使用

一个简单的使用示例：
```C++
template <typename T>
class container {
public:
    container(): num_elems(0) {} 

    T* begin() const noexcept { return elems; }
    T* end() const noexcept { return &elems[num_elems];  } 

    bool emtpy() {
        return num_elems <= 0 ? true : false;
    }

    void push(const T& elem) { 
        elems[num_elems++] = elem;
    }

    void pop() {
        if (!emtpy())
            throw vector_exception("container<>::pop(): empty stack!");
        num_elems--;
    }

    T top() const {
        if (!emtpy())
            throw vector_exception("container<>::top(): emtpy stack!");
        return elems[num_elems - 1];
    }

    // using const_iterator = const T*;
    // using iterator       = T*;
    typedef T* iterator;
    typedef const T* const_iterator;
private:
    T* elems = new T[10000];
    size_t num_elems;
};

template <typename T>
void print_container(const T& coll) {
    typename T::const_iterator pos;
    typename T::const_iterator end(coll.end());

    for (pos = coll.begin(); pos != end; ++pos) {
        std::cout << *pos;
    }
}

int main() {
    container<int> c_int;    
    
    c_int.push(3);
    c_int.push(4);
    c_int.push(5);

    print_container(c_int);
}
```
`const_iterator`和`iterator`是在`container`中声明的类型，两个都作为`container`的迭代器使用。

在`print_container`函数中使用迭代器`const_iterator`对整个`c_int`进行了遍历，需要注意的是，如果使用的类型例如`const_iterator`依赖于某个类（例如`container`)，那么在其前面就需要加上`typename`关键字。因此有必要在后续的容器中都声明有迭代器类型`const_iterator`或`iterator`。
```C++
typedef T* iterator;
typedef const T* const_iterator;

// or

using iterator = T*;
using iterator = const T*;
```

## `.template`构造：
```C++
template <typename T, int N>
class test {
public:
    test(const std::string& str): m_str(std::to_string(N)) { }
    
    template <typename T2 = double>
    void show() const {
        std::cout << m_str << '\n' 
                  << "T2: ";
    }
private:
    std::string m_str;
};

template<typename T>
class test<T, 10> {
public:
    test(const std::string& str): m_str(std::to_string(10)) { }
    
    template <typename T2>
    void show() const {
        std::cout << m_str << '\n'
                  << "T2: ";
    }
private:
    std::string m_str;
};

template <typename T, int N>
void select_test(const test<T, N>& t) {
    t.template show<int>();
}

int main() {
    select_test(test<int, 10>("ppqwqqq"));
}
```
此处`test`中的`show()`方法依赖于模板参数`T2`，而在函数模板`select_test`中，调用的是依赖模板参数的对象`t`的`show`方法，为了让编译器能够识别`<>`符号，需要在其前面加上`.template`来帮助编译器进行区分。


`->template`间接构造：
```C++
template <typename T, int N>
void select_test(const test<T, N>* t) {
    t->template show<int>();
}

int main() {
    select_test(new test<int, 10>("ppqwqqq"));
}
```

## 使用`this->`
```C++
void exit() { std::cout << "exit()"; }

template <typename T>
class Base {
public:
    void exit() { std::cout << "class exit()"; }
};

template <typename T>
class Derived: public Base<T> {
public:
    void foo() {
        Base<T>::exit();
        /* or this->exit();  */
    }
};

int main() {
    Derived<int>* d;
    d->foo();
}
```
子类`Derived`的`foo()`方法中调用的`exit()`可能不是基类`Base`中的`exit()`而是外部定义的`exit()`或者调用时会导致其他错误，因此对于在子类中调用基类的方法，并且依赖模板参数的符号(函数或者成员变量)，需要在子类调用基类的方法前加上`this->`或`Base<T>::`来指定成员的访问。

总之，在子类中调用基类中的方法时，要标明这个方法是从基类中来的，不然傻逼类模板不知道调用哪个方法，然后瞎调用。



