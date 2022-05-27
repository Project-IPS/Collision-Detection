cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Srs
    src/*.c*
)
file(GLOB_RECURSE Hdrs
    include/*.h*
)

add_library(Utilities STATIC ${Srs} ${Hdrs})


target_include_directories(Utilities PUBLIC include)