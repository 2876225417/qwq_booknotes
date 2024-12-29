#ifndef STRING_H_
#define STRING_H_

#include <cstddef>
#include <iostream>


namespace qwq_string {
    class custom_string {
    public:
        explicit custom_string();
        explicit custom_string(const char*);

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

        friend
        bool operator==(const custom_string& lhs, std::nullptr_t) {
            std::cout << "Compared with nullptr_t\n";
            return lhs.m_str == nullptr;
        }

        operator const char* () {
            return m_str;
        }

        operator bool () {
            std::cout << "bool() const!\n";
            return m_str == nullptr;
        }

        operator const char* () const {
            return m_str;
        }


    private:
        char* m_str;
    };
}

#endif