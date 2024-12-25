


针对三个参数的模板

```C++
#include <string>
#include <cstring>
#include <iostream>

template <typename T>
inline const T& max(const T& a, const T& b) {
    return a > b ? a : b;
}

// 此处声明
// inline const T& max(const int&, const int&);
// 可以确保在下面的函数模板中被重载调用

template <typename T>
inline const T& max(const T& a, const T& b, const T& c) {
    return max(max(a, b), c);
}

// max函数的 int 版本声明于该版本被调用的后面，无法被找到，重载时选择
// 两个参数的函数模板
inline const int& max(const int& a, const int& b) { 
    return a > b ? a : b;
}

int main() {
    auto t = max(123, 124, 125);
}
```
总结：编译器会先调用有明确类型的函数版本，否则选择函数模板。


特化的模板可以和基本类模板的实现完全不同。

**局部特化**

多模板同等程度的匹配：
如果有多个局部特化同等程度地匹配某个声明，那么就称该声明
具有二义性：
```C++
MyClass<int, int> m; 同等程度匹配 MyClass<T, T> 和 MyClass<T, int>。

MyClass<int*, int*> m; 同等程度匹配
MyClass<T, T> 和 MyClass<T1*, T2*>
```
解决第二种二义性，提供一个指向相同类型指针的特化：
```C++
template <typename T>
class MyClass<T*, T*> {
    ......
};
```