#include "string.h"
#include <cstring>

/** A simple hand made string
 *  
 */


namespace qwq_string {

    custom_string::custom_string(): m_str{ new char[1]('\0') } { }

    custom_string::~custom_string() noexcept { delete[] m_str; }
    
    custom_string::custom_string(char* str) {
        if (str == nullptr) {
            m_str = new char[1]('\0');
        } else {
            m_str = new char[strlen(str) + 1];
            strcpy(m_str, str);
            m_str[strlen(str)] = '\0';
        }
    }

    custom_string::custom_string(const custom_string& rhs) {
        m_str = new char[strlen(rhs.m_str) + 1];
        strcpy(m_str, rhs.m_str);
        m_str[strlen(rhs.m_str)] = '\0';
    }

    custom_string::custom_string(custom_string&& rhs) {
        m_str = rhs.m_str;
        rhs.m_str = nullptr;
    }




}