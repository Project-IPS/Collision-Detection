cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
add_executable(Collision main.cpp config.hpp )




target_link_libraries(Collision PRIVATE Utilities)
