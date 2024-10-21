cmake_minimum_required(VERSION 3.14)
project(hashtable C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_subdirectory(googletest)
#enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#add_compile_options(-fsanitize=address -Wall)
#add_link_options(-fsanitize=address)

set(Headers
    src/hashtable.h
)
set(Sources
    src/operators.cpp
    src/ctors.cpp
    src/methods.cpp
    src/main.cpp
)

add_library(hashtable STATIC ${Sources} ${Headers})

add_subdirectory(test)
