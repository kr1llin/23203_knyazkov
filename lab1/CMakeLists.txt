cmake_minimum_required(VERSION 3.14)
project(hashtable C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(googletest)

enable_testing()

set(Headers
    hashtable.h
)
set(Sources
    operators.cpp
    ctors.cpp
    methods.cpp
    main.cpp
)

add_library(hashtable STATIC ${Sources} ${Headers})

add_subdirectory(test)
