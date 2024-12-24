#include "message.h"

#include <iostream>
#include <string>

std::ostream& message::print_obj(std::ostream& os) {
    os << "This is an example from CMake!\n";
    os << message_;
    return os;
}




