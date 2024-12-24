cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(qwq_main)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)


add_executable(qwq_main 
    qwq_main.cpp
    stack.hpp
    item.hpp
)



 