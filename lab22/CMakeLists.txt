# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ForthProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories (if needed)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Specify the source files
set(SOURCES
    forth.cpp
    scanner.cpp
)

# Specify the header files (optional, for IDEs)
set(HEADERS
    definition.hpp
    forth.hpp
    scanner.hpp
    Token.hpp
)

# Create the executable
add_executable(forth ${SOURCES} ${HEADERS})
