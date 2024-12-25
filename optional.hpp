#pragma once


struct nullopt_t { };
inline nullopt_t nullopt;

template <typename T>
struct Optional {
    T val;
    bool has_val;
    

    Optional(T val_): val(val_), has_val(true) { }
    Optional(nullopt_t): val(), has_val(false) { }
    Optional(): val(), has_val(false) { }
};




