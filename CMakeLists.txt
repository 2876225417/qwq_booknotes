cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(cookbook)
set(CMAKE_CXX_STANDARD 23)


add_library(message-objs
    OBJECT
    message.h
    message.cpp
)

add_library(message-shared
    SHARED
    $<TARGET_OBJECTS:message-objs>
)

set_target_properties(message-shared
    PROPERTIES
    OUTPUT_NAME "message"
)

add_library(message-static
    STATIC
    $<TARGET_OBJECTS:message-objs>
)
 
set_target_properties(message-static
    PROPERTIES
    OUTPUT_NAME "message"
)


add_executable(cookbook
    cookbook.cpp
)

target_link_libraries(cookbook
    message-static
)



