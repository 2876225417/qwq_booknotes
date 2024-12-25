

#include "stack.hpp"


#include "item.hpp"
#include "message.h"

#include <iostream>
#include <string>

int main() {
    point<int> p_1{1, 1, 1};
    std::cout << "p_1's info: " << p_1;

    


    qwq_stack::stack<int> s1;
    s1.push(23);
    s1.push(24);

    std::cout << s1 << std::endl;

    qwq_stack::stack<std::string> s_str;
    s_str.push("ppqwqqq");
    s_str.push("puoond");
    std::cout << s_str << '\n';

    qwq_stack::stack<point<int>> s_p;
    s_p.push(point{1, 2, 3});
    s_p.push(point{1, 3, 4});
    s_p.push(std::move(p_1));
    std::cout << s_p << '\n';

    qwq_stack::stack<int> s_i_1;
    s_i_1.push(4);
    qwq_stack::stack<int> s_i_2;
    s_i_2.push(2);
    qwq_stack::stack<int> s_i_3;
    s_i_3.push(4);
    qwq_stack::stack<int> s_i_4;
    s_i_4.push(5);
    
    qwq_stack::stack<float*> s_ptr;
    
    float f_1 = 23, f_2= 23, f_3 = 24;
    
    s_ptr.push(&f_1);
    s_ptr.push(&f_2);
    s_ptr.push(&f_3);
    std::cout << s_ptr << '\n';

    qwq_stack::unique_stack<point<int>, point<int>> us1; 
    qwq_stack::unique_stack<point<double*>, point<int>> us2; 
    qwq_stack::unique_stack<point<int>, point<int>*> us3; 
    qwq_stack::unique_stack<point<point<int*>>, point<double*>> us4; 
    qwq_stack::unique_stack<point<int*>*, point<int*>*> us5;
    
    qwq_stack::default_stack<point<int>> de_stack;
    point<int> pi_1{ 1, 2, 3 };
    point<int> pi_2 {3, 4, 5 };
    point<double> pd_1{ 2.2, 3.3, 4.4 };

    de_stack.push(std::move(pi_1));
    de_stack.push(std::move(pi_2));
    
    std::cout << de_stack << '\n';


}