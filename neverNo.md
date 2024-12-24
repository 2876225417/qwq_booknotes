# Similar types 类似类型

一般地，忽略顶层的cv-qualification，具有如下特点的为 similar types:
1. 它们是相同类型；
2. 它们都是指针，且指向相似的类型。
3. 它们都是指向相同类的成员变量，且这些成员变量的类型相似。
4. 它们都是 array，并且 array 元素的类型相似。

总而言之，最小的元素的类型相似即为 similar types。

> 例如：  
> `const int* const*` 和 `int**`  
> `int (*)(int*)` 和 `int (*)(const int*)`  
> `const int (*)(int*)` 和 `int (*)(int*)`  
> `std::pair<int, int>`和 `std::pair<const int, int>`  
> 忽略`const`，它们都是一样的。

`cv_qualifier`：`cv`是`const`和`volatile`的组合，代表常量性和易变性。

`cv_i`表示一个`const`和`volatile`的修饰符集合。

`P_i`表示类型修饰符的某些信息，例如指针类型、指向成员的指针等：
* **Pointer to**:表示一个指针类型。
* **Pointer to member of class C_i of type**:表示一个指向成员变量的指针。
* **Array of N_i**:表示数组类型。
* **Array of unknown bound**:变长数组。

`U`是原始类型（未经过任何指针、数组等修饰过的类型）。

**修饰符分解(Qualification Decomposition)**

**QD**是把一种类型拆解成`cv_i`和`P_i`：
* **cv_0,cv_1,...,cv_n**：多个`const`和`volatile`修饰符的集合。
* **P_0,P_1,...,P_n-1**：不同的指针、数组或引用类型。

对一个`T`的分解：
`T= cv_0 P_0 cv_1 P_1 ... cv_n-1 P_n-1 cv_n U`

数组元素类型的`cv`修饰符会继承给数组的修饰符。

> 分解: `const volatile int* const arr[10]`  
> 1. 分解数组 `arr[10]`  
> `arr[10]`是一个数组,`P_0`是**array of 10 of pointer to int**。  
> 2. 分解指针  
> 每个元素是`const int*`，其中`P_1`是**pointer to const int**。  
> 3. `const`和`volatile`：  
> 直接修饰`arr`数组本身
> >最终:  
> > cv_0: const volatile  
> > P_0: Array of 10 of pointer to  
> > cv_1: const  
> > P_1: pointer to  
> > U: int 

如果两个类型在**QD**后：
* 具有相同的**n**
* 类型**U**相同
* 对应的**P_i**相同或者其中一个是**N_i**的数组并且另一个是变长数组。

临时实体化(Temporary Materialization)  
任何完整类型的prvalue都可以转换为同类型的xvalue。  
如果`T`是一个类，那么该类的析构函数不允许被`delete`且`public`。

```C++
struct S { int m; }
int i = S().m;
```
此时,`S()`prvalue会被转换为xvalue。

临时实体化发生在：
* 将引用绑定到 prvalue 时
* 访问类 prvalue 的非静态成员时。
* 调用类 prvalue 的隐式对象成员函数时。
* 在数组 prvalue 上执行数组到指针的转换或下标时。
* 在括号中使用初始化列表初始化一个`std::initialized_list<T>`对象时。

`const_cast`转换的结果:  
* lvalue: 当目标类型为 lvalue 引用 或者 函数类型的 rvalue 应用时；
* xvalue：当目标类型为对象类型的 rvalue 引用时；
* prvalue：当目标类型不是lvalue和xvalue时。

去除`const`限定：
* 使用`const_cast`。
* 去除`const`限定同时也会去掉`volatile`限定，`cv`总绑定在一起。
* 对于指向函数的指针和指向成员函数的指针,`const_cast`无法去掉`const`。

注意，当对一个`const`对象进行了`const_cast`操作后，无法再使用非`const`或非`volatile`引用进行访问该非`const`对象。

使用示例:
```C++
struct type {
    int i;

    type(): i(3) {}

    void f(int v) const {
        const_cast<type*>(this)->i = v;
    }

};

int main() {
    int i = 3;
    const int& rci = i;
    const_cast<int&>(rci) = 4;
    std::cout << "i = " << i << '\n';

    type t;
    t.f(4);
    std::cout << "type::i: " << t.i << '\n'; 

    const int j = 3;
    [[maybe_unused]]
    int* pj = const_cast<int*>(&j);
    // *pj = 4; // -> undefined behavior

    [[maybe_unused]]
    void (type::* pmf)(int) const = &type::f;
    // const_cast<void(type::*)(int)>(pmf);
    // const_cast does not work on member function
    return EXIT_SUCCESS;
}
```


## `static_cast`一种显式类型转换

语法: `static<目标类型>(表达式)`

在知道转换是安全的前提下才使用`static_cast`进行转换。

1. 引用转换：从lvalue到引用的转换  
   表达式类型为`cv1 Base`的左值，目标类型是`cv2 Derived`的引用时，转换只在以下情况有效：
   * `Derived`是一个完整的类型。
   * `Base`是`Derived`的基类。
   * `cv1`的限定符不比`cv2`更严格。
   * UB:如果`Base`是虚基类，或者表达式没有引用`Derived`类型的基类子对象，则会导致未定义行为：
   ```C++
   struct Base{};
   struct Derived: Base {};
   Derived d;
   Base& br = d;
   static_cast<Derived&>(br);
   ```
2. rvalue引用转换：
   如果目标类型是`Derived`的右值引用，且`表达式`是类型为`Base`的右值(xvalue)，并且`Base`是`Derived`的基类，那么可以转换。
3. 转换为`void`：目标是`void`，则结果为丢弃表达式的值。
4. 指针转换：可以将`Base`指针转换为`Derived`指针，但是`Derived`必须是`Base`的直接派生类。
5. 