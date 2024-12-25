#ifndef STRING_H_
#define STRING_H_

#include <iostream>


namespace qwq_string {
    class custom_string {
    public:
        explicit custom_string();
        explicit custom_string(char* str);
        explicit custom_string(const custom_string&);
        explicit custom_string(custom_string&&);
        ~custom_string() noexcept;

        friend inline  
        std::ostream& operator<<(std::ostream& os, const custom_string& obj) {
            size_t cnt = 0;
            while (obj.m_str[cnt] != '\0')
                os << obj.m_str[cnt++];
            return os;
        }

    private:
        char* m_str;
    };
}

#endif