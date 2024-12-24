#include "message.h"

#include <iostream>
#include <string>

message::message(const std::string& m_): message_(std::move(m_)) { }


std::ostream& message::print_obj(std::ostream& os) {
    os << "This is an example from CMake!\n";
    os << message_;
    return os;
}




