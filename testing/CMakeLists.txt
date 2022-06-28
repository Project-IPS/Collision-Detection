find_package(Catch2 3 REQUIRED)
file(GLOB_RECURSE Srs
    ./*.c*    
)
add_executable(tests aabbtests.cpp bvhtests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE Utilities)