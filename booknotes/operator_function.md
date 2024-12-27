


# 类的操作符重载


`+`、`-`、`+=`、`-=`等操作符


## 成员函数和友元函数操作符重载
```C++
class meta {
public:

    meta(int a, int b): m_a(a), m_b(b) { }

    friend std::ostream& operator<<(std::ostream& os, const meta& obj) {
       os << "m_a: " << obj.m_a << ' '
           << "m_b: " << obj.m_b << '\n';
        return os;
    }

    // 友元函数
    friend 
    meta& operator+=(meta& lhs, meta& rhs) {
        lhs.m_a += rhs.m_a;
        lhs.m_b += rhs.m_b;
        return lhs;
    }

    friend
    meta& operator+(meta& lhs, meta& rhs) {
        lhs.m_a += rhs.m_a;
        lhs.m_a += rhs.m_a;
        return lhs;
    }
    
    /* // 成员函数
    meta& operator+=(meta& obj) {
        this->m_a += obj.m_a;
        this->m_b += obj.m_b;
        return *this;
    }

    meta& operator+(meta& obj) {
        this->m_a += obj.m_a;
        this->m_b += obj.m_a;
        return *this;
    }
    */

private:
    int m_a;
    int m_b;
};
```
操作符的成员函数和友元函数不能同时存在。否则编译器不知道使用哪一个。


其中成员函数作为类的一部分，可以访问类的私有成员变量。

友元函数也是如此，可以访问类的私有成员变量。

使用友元函数时需要多一个参数，即该类本身。

`+=`、`+`操作返回该类的引用，也可以是该类的实例。

返回类的引用
```C++
/* 友元函数操作符重载 */
friend
A& operator+=/*or <+> <-> <-=> */(A& lhs, A& rhs) {
    /* 一些操作 */
    return lhs;
}

/** 成员函数操作符重载 
 *  如下同理
 */
A& operator+=(A& obj) {
    /* 一些操作 */
    return *this;
}
```

区别： 然而对于在`class`外重载的操作符无法完成上述操作，如果要完成，得需要通过类内部实现的方法来在类外获取这些私有的成员变量，来完成重载：
```C++
class A {
    /* ... */
    A& plus(A& obj) { /* ... */ return *this; }
private:
    int a;
    int b;
};


A& operator+(A& lhs, A& rhs) {
    /* ... */
    /** 如果此处未能够获取 类A 中所需的成员变量 来达到目标
     *  那么该重载操作无法完成
     *  此不是在类中声明，外部实现的方法!!!
     *  在外部定义的操作符重载不能实现!!! 
     */
    
}
```