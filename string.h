#ifndef STRING_H_
#define STRING_H_


namespace qwq_string {
    class custom_string {
    public:
        explicit custom_string();
        explicit custom_string(char* str);
        explicit custom_string(const custom_string&);
        explicit custom_string(custom_string&&);
        ~custom_string() noexcept;

    private:
        char* m_str;
    };
}

#endif