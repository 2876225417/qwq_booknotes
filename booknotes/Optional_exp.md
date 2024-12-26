



## `tag`类使用技巧

使一个类的构造函数只能接受**自己创建的类**进行构造。

小彭老师的示例：
使用`tag`类来规定构造使用的参数：
```C++
// 定义计算内核：
// compute_cpu_kernel 
// compute_gpu_kernel
// 用来初始化 compute_kernel 时的参数类型

inline struct compute_cpu_kernel {
    compute_cpu_kernel() = default;
} cck;

inline struct compute_gpu_kernel {
    compute_gpu_kernel();
} cgk;

inline struct compute_kernel {
    // 仅接受 compute_cpu_kernel 
    compute_kernel(compute_cpu_kernel);
    // 仅接受 compute_gpu_kernel
    compute_kernel(compute_gpu_kernel);
};

computer_kernel ck_1(ckk);
computer_kernel ck_2(cgk);
```


在类进行构造时，如果没有指定对`union`成员进行初始化（或构造），那么`union`成员不会自动初始化（或构造）：
```C++
struct C {
    C(int a, int b): m_a(a), m_b(b) { std::cout << "ctor()"; }

private:
    int a;
    int b;
};

struct test {
    union {
        /* 套一层 union */
        C c;
    }; // 可以编译成功

    // C c; // 直接声明，但是不在构造函数中初始化
    // 不行！编译不成功
    // struct 内的成员必须显式构造！

    test() { }

};
```

针对一些平凡类型的成员变量，在类析构时需要手动调用这些成员变量的析构函数：
```C++
// 平凡类型
// 结构体
struct S {

};

// 类
class C {

};

// 带有析构函数的对象
class C_dtor {

    ~C_dtor() { }
};

struct S_dtor {
    ~S_dtor() { }
};

// 销毁此类对象时，需要手动调用其析构函数
```




