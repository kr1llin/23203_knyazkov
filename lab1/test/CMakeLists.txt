cmake_minimum_required(VERSION 3.14)
project(lab1Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Sources
    operators_tests.cc
    methods_tests.cc
    ctors_tests.cc
)

add_executable(lab1Tests ${Sources})
target_link_libraries(lab1Tests PUBLIC
    gtest_main
    hashtable
)

add_test(
    NAME lab1Tests
    COMMAND lab1Tests
)
