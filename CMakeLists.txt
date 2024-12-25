cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(qwq_main)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)


set(STACK_EXCEPT stack_except)


add_library(${STACK_EXCEPT}
    stack_except.h stack_except.cpp
)

add_executable(qwq_main 
    qwq_main.cpp
    stack.hpp
    item.hpp
)

target_link_libraries(qwq_main ${STACk_EXCEPT})



 