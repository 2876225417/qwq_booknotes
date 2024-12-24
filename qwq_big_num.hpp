#ifndef QWQ_BIG_NUM_HPP
#define QWQ_BIG_NUM_HPP

#include <iostream>
#include <string>

namespace qwq_big_num {
    inline std::string big_int_add(const std::string& num_1, const std::string& num_2) {
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

    inline bool is_greater_of_equal(const std::string& num_1, const std::string& num_2) {
        if (num_1.size() > num_2.size()) return true;
        if (num_1.size() < num_2.size()) return false;
        return num_1 >= num_2;
    }

    inline std::string big_int_substract(const std::string& num_1, const std::string& num_2) {
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

}
#endif // QWQ_BIG_NUM_HPP