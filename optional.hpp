#pragma once

#include <exception>

namespace qwq_optional {
    

    struct optional_exception: public std::exception {
        optional_exception() = default;
        virtual ~optional_exception() = default;

        const char* what() const noexcept override {
            return "bad optional access";
        }
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

        optional(T val): m_value(val), m_has_value(true) { }
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

        T value() const {
            if (!m_has_value) 
                throw optional_exception();
            return m_value;
        }
    
    };



}



