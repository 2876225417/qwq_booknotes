
# `std::nullptr_t` 和 `nullptr`

可以看作`nullptr_t`是一个类型，而`nullptr`是它的一个实例。

其实`using nullptr_t = decltype(nullptr)`。

这个类型的特别之处在于它自身不是一个指针或一个成员变量指针类型，
并且可以被显式转换为任意类型的指针。

对于`nullptr`而言，类似的转换存在于任何`null`指针常量中，其中包括`std::nullptr_t`类型的值和`NULL`宏。

> define NULL 0

因此，如果一个函数有多个重载，如果其中一个重载的参数为`nullptr`，那么为这个函数添加`std::nullptr_t`的重载是很有必要的，这样可以避免**ambiguous`的情况：
```C++
void func(int*) { std::cout << "int*"; }
void func(double*) { std::cout << "double*"; }
void func(std::nullptr_t) { std::cout << "nullptr_t"; }
/* ... */
func(nullptr); 
// 此处 func 选择的重载类型就是 void func(std::nullptr_t);
// 如果没有 std::nullptr_t 类型的重载，那么就会导致 ambiguous
```

其中`sizeof(std::nullptr_t)`等于`sizeof(void *)`。


`nullptr`是一个指针字面量，并且是`std::nullptr_t`类型的纯右值。

> **literal**字面量
> 在编译期即可确定值
> **non-literal**非字面量值
> 需要在运行时确定值

```C++
template <typename T>
constexpr T clone(const T& t) {
    return t;
} /* 需要在运行确定值 */
void g(int*);

g(clone(0));        // 错误，clone<int> 不能将 int 隐式转换为 int*
g(clone(NULL));     // 错误，同上
g(clone(nullptr));  // 正常，nullptr可以转换为任何类型
```


