#ifndef QWQ_BIG_NUM_HPP
#define QWQ_BIG_NUM_HPP

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include "string.h"


namespace qwq_big_num {
    using qwq_string::custom_string;
    class num_exception: public std::exception {
    public:
        num_exception() = default;
        num_exception(const char* err_msg): m_err_msg(const_cast<char*>(err_msg)) { }
        
        virtual ~num_exception() = default;
        
        const char* what() const noexcept override {
            return !m_err_msg ? "Bad num calculating...\n" : m_err_msg;
        }

    private:
        custom_string m_err_msg;      
    };




    inline
    std::string big_int_add(const std::string& num_1, const std::string& num_2) {
        if (num_1.size() < num_2.size()) return big_int_add(num_2, num_1);

        std::string result = "";
        int carry = 0;
        int i = num_1.size() - 1;
        int j = num_2.size() - 1;
        
        while (i >= 0 || j >= 0 || carry) {
            int digit_1 = (i >= 0) ? num_1[i] - '0': 0;
            int digit_2 = (j >= 0) ? num_2[j] - '0': 0;
            
            int sum = digit_1 + digit_2 + carry;
            carry = sum / 10;
            result += (sum % 10) + '0';
            i--;
            j--;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    inline
    bool is_greater_of_equal(const std::string& num_1, const std::string& num_2) {
        if (num_1.size() > num_2.size()) return true;
        if (num_1.size() < num_2.size()) return false;
        return num_1 >= num_2;
    }

    inline
    std::string big_int_substract(const std::string& num_1, const std::string& num_2) {
        if(!is_greater_of_equal(num_1, num_2)) return "-" + big_int_substract(num_2, num_1);

        std::string result = "";
        int borrow = 0;
        int i = num_1.size() - 1;
        int j = num_2.size() - 1;

        while (i >= 0 || j >= 0 || borrow) { 
            int digit_1 = (i >= 0) ? num_1[i] - '0' : 0;
            int digit_2 = (j >= 0) ? num_2[j] - '0' : 0;

            int diff = digit_1 - digit_2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else borrow = 0;

            result += diff + '0';
            i--;
            j--;
        }

        while (result.size()  > 1 && result.back() == '0')
            result.pop_back();

        std::reverse(result.begin(), result.end());
        return result;
    }

    inline
    std::string big_int_multiply(const std::string& num_1, const std::string& num_2) {
        if (num_1 == "0" || num_2 == "0") return "0";

        int len_1 = num_1.size();
        int len_2 = num_2.size();

        std::vector<int> _res(len_1 + len_2, 0);

        for (int i = len_1 - 1; i >= 0; i--) 
            for (int j = len_2 - 1; j >= 0; j--) {
                int dig_1 = num_1[i] - '0';
                int dig_2 = num_2[j] - '0';
                int pro   = dig_1 * dig_2;

                int pos_1 = i + j;
                int pos_2 = i + j + 1;
                // int pos_2 = pos_1 + 1;
                int sum   = pro + _res[pos_2];

                _res[pos_2] = sum % 10;
                _res[pos_1] += sum / 10; 
            }
        
        std::string res = "";
        for (int i = 0; i < _res.size(); i++) 
            if (!(res.empty() && _res[i] == 0))
                res += _res[i] + '0';

        return res;
    }

    inline
    std::string big_int_divide(const std::string& num_1, const std::string& num_2){
        if (num_2 == "0")
            throw num_exception("Cannot divided by 0!");
        
        if (num_1 == "0")
            


        



        return "";
    } 




}
#endif // QWQ_BIG_NUM_HPP