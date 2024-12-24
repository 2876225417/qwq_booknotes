#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iosfwd>
#include <string>

class message {
public:

    message(const std::string& m): message_(std::move(m)) { }
    
    friend std::ostream& operator<<(std::ostream& os, message& obj) {
        return obj.print_obj(os);
    }

private:
    std::string message_;
    std::ostream& print_obj(std::ostream& os);
};


#endif