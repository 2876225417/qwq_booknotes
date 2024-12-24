# __PRETTY_FUNCTION__

`__PRETTY_FUNCTION__`可以显示函数的具体签名，包括函数模板：
```C++
#define LOG(x) (std::cout << __FILE__ << ": " \
                          << __LINE__  << ": " \
                          << __PRETTY_FUNCTION__ << ": " \
                          << (x) << '\n');


void func() { LOG("func()"); }

void func(int a) { LOG("func()"); }

void func(size_t b) { LOG("func()"); }

template<typename T>
void func(T t) { LOG("func()"); }

int main() {
    func();
    func(1);
    size_t t = 2;
    func(t);    
    func("qwq");
}
```
输出结构：文件名: 行号: 函数具体签名

输出：
```
C:\Users\28762\Desktop\OS_CT_ASM\Sources\main.cpp: 18:void func(): func()
C:\Users\28762\Desktop\OS_CT_ASM\Sources\main.cpp: 20:void func(int): func()
C:\Users\28762\Desktop\OS_CT_ASM\Sources\main.cpp: 22:void func(size_t): func()
C:\Users\28762\Desktop\OS_CT_ASM\Sources\main.cpp: 25:void func(T) [with T = const char*]: func()
```

# 准确获取被实例化的模板的类型(单个模板参数的模板)

```C++
template <class T>
std::string get_type_name() {
    std::string str = __PRETTY_FUNCTION__;
    std::cout << "original str: " << str << '\n';
    auto pos = str.find("T = ") + 4;            // 起始位置
    std::cout << "pos: " << pos << '\n'; 
    auto pos2 = str.find_first_of(";]", pos);   // 终止位置
    std::cout << "pos2: " << pos2 << '\n';
    return str.substr(pos, pos2 - pos);
}

// 即时在命名空间中的类型，也可以获取
namespace utils {
    struct my_struct {

    };
}

int main() {
    std::cout << get_type_name<utils::my_struct>();
}
```
输出:
```
original str: std::string get_type_name() [with T = utils::my_struct; std::string = std::__cxx11::basic_string<char>]
pos: 38
pos2: 54
utils::my_struct 
```


# 获取枚举类型的值

```C++
template <typename T, T N>
std::string get_param_value() {
    std::string str = __PRETTY_FUNCTION__;

    std::endl(std::cout << "original str: " << str);

    auto pos = str.find("N = ") + 4;
    auto pos2 = str.find_first_of(";]", pos);
    return str.substr(pos, pos2 - pos);
}

enum color {
    RED = 1, BLUE = 2, YELLOW = 3, GREEN = 4,
};

int main() {
    // get_param_value 中的第二个参数只接受编译期参数(constexpr)
    std::cout << get_param_value<color, (color)2>() << '\n' // 在枚举范围内
              << get_param_value<color, (color)7>();        // 不在枚举范围内
}
```
输出:
```
original str: std::string get_param_value() [with T = color; T N = BLUE; std::string = std::__cxx11::basic_string<char>]
BLUE
original str: std::string get_param_value() [with T = color; T N = (color)7; std::string = std::__cxx11::basic_string<char>]
(color)7
```


