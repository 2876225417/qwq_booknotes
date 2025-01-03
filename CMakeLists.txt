cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(qwq_main)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)

find_package(Boost REQUIRED COMPONENTS
    system
    filesystem
    asio
    beast
)

set(STACK_EXCEPT stack_except)
set(CUSTOM_STRING custom_string)

add_library(${STACK_EXCEPT}
    STATIC
    stack_except.h stack_except.cpp
)

add_library(${CUSTOM_STRING}
    STATIC
    string.h string.cpp
)

add_executable(qwq_main 
    qwq_main.cpp
    stack.hpp
    item.hpp
    optional.hpp
)

target_link_libraries(qwq_main 
    ${STACK_EXCEPT}
    ${CUSTOM_STRING}    
    Boost::boost
    Boost::system
    Boost::filesystem
    Boost::asio
    Boost::beast
    ws2_32
)



 