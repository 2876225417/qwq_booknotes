# `decltype` 关键字

检查实体的声明类型和表达式的值类别。

语法：
```C++
decltype( 实体 )
decltype( 表达式 )
```


好玩的东西：
```C++
void func(int a) { std::cout << "a: " << "nullptr!"; }

int main() {
    decltype(func)* k = func;
    
    k(3);
    auto t = k;
    t(5);
    /* 函数指针 */
    void (*m)(int) = func;
    m(6);
}
```
将函数名传递给`decltype`作为参数使用，`delctype`推导出函数指针。

















