cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(main)
set(CMAKE_CXX_STANDARD 23)


# find_package(Boost REQUIRED COMPONENTS filesystem system asio beast)

# find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
 
find_package(fmt REQUIRED)

add_executable(main
    tmpt.cpp
    max.hpp
    qwq_sort.hpp
    qwq_big_num.hpp
)

# target_link_libraries(main Boost::asio Boost::beast)
# target_link_libraries(main Qt6::Core Qt6::Gui Qt6::Widgets)
# target_link_libraries(main fmt::fmt)