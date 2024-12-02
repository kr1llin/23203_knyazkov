cmake_minimum_required(VERSION 3.10)

project(ForthProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    forth.cpp
    scanner.cpp
    parser.cpp
    expressions.cpp
    factory.cpp
    UserInterface.cpp
)

set(HEADERS
    forth.hpp
    scanner.hpp
    Token.hpp
    parser.hpp
    expressions.hpp
    factory.hpp
    UserInterface.hpp
)

add_executable(forth ${SOURCES} ${HEADERS})
