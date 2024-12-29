#pragma once

#include <exception>
#include "string.h"

namespace qwq_optional {
    
    using::qwq_string::custom_string;
    struct optional_exception: public std::exception {    
        optional_exception(): m_err_msg(nullptr) { }
        optional_exception(const char* err_msg): 
        m_err_msg(err_msg) { }    

        virtual ~optional_exception() = default;

        const char* what() const noexcept override{
            if (m_err_msg != nullptr)
                return m_err_msg;
            return "Bad optional access";
        }
        private: custom_string m_err_msg;
    };
    

    /** Customized __tag__ struct 
     *  nullopt struct 
     *  instance nullopt 
     *
     * struct nullopt_t { };
     * inline nullopt_t nullopt;
     * 
     * @brief structure
     * for null initialization
     */
    inline constexpr struct nullopt_t { } nullopt; 
    

    template <typename T>
    struct optional {
        bool m_has_value;
        
        union {
            T m_value;
            nullopt_t m_nullopt;
        };

        optional(T val): m_has_value(true), m_value(val) { }
        optional(nullopt_t): m_has_value(false), m_nullopt() { }
        optional(): m_has_value(false), m_nullopt() { }

        ~optional() {
            if (m_has_value)
                m_value.~T();
            /** else m_nullopt.~nullopt_t() 
             *  This is a puzzle......
             */
        }

        bool has_value() const {
            return m_has_value;
        }

        // lvalue
        T& value()& {
            if (!m_has_value) 
                throw optional_exception("T& Bad optional access");
            return m_value;
        }

        const T& value() const& {
            if (!m_has_value)
                throw optional_exception("const T& bad optional access");
            return m_value();
        }

        // rvalue
        T&& value() && {
            if (!m_has_value)
                throw optional_exception("T&& bad optional access");
            return m_value;
        }

        const T&& value() const&& {
            if (!m_has_value)
                throw optional_exception("const T&& bad optional access");
            return m_value;
        }

    
    };



}



