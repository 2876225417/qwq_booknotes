



# 类型转换的特征


1. 类型转换定义在源类中；
2. 须由`operator`修饰，函数名称是目标类型或目标类型。
3. 函数没有参数，没有返回值，但是有`return`语句，在`return`语句中返回目标类型数据或调用目标类的构造函数。

类型转换函数的类别：
1. 对象向基本数据类型转换
```C++
#include <iostream>

class test {
public:
    test(const double& d): d_(d) { }
    
    operator int() const {
        std::cout << "Type converting to int...!\n";
        return static_cast<int>(d_);
    }

private:
    double d_;
};


int add(int a, int b) {
    return a + b;
}

int main() {
    test t1(2.2);
    test t2(3.3);

    std::cout << add(t1, t2) << '\n';
}



```


重拾：
1. `<type_name> operator()`的作用是让对象能够像被函数一样调用，典型的例子是，仿函数的实现:
   ```C++
   struct {
        void operator()(const std::string& str) {
            std::cout << str << '\n';
        }
   } instance;
   ```

2. `operator <type_name>()`就是上面提到的内类类型转换：
   ```C++
    class test {
    public:
        test(const double& d): d_(d) { }
        operator int() {
            return static_cast<int>(d_);
        }
    private: double d_;
    };
   ```


## 个人理解：
在类`A`中实现了`operator <type_name> ()`，意思为在`A`的实例(或临时)以`<type_name>`的类型被调用时，会使用对应的`type_name`方法的实现：
```C++
// 例如


class A {
public:
    A(const double& b): b(b_) { }
    
    /** 当 A 被以 int 类型调用时会使用下面实现的方法 
     *  通常是返回 A 中对应的类型的成员
     *  但是这个可以随便实现
     */
    
    operator int() {

    }
private:
    double b_;
};


void op(int a) { }


int main() { 
    op(A(23));
    /* 对象 A 将会调用 `operator int()`的实现 */
}


```