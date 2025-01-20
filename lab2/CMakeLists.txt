cmake_minimum_required(VERSION 3.10)

project(ForthProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

link_directories(/usr/local/lib)

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
# set(SANITIZER_FLAGS "-fsanitize=address")


enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
src/main.cpp
src/forth.cpp
src/scanner.cpp
src/interpreter.cpp
src/expressions.cpp
src/factory.cpp
src/UserInterface.cpp
src/ExecutionContext.cpp
)

set(HEADERS
src/forth.hpp
src/scanner.hpp
src/Token.hpp
src/interpreter.hpp
src/expressions.hpp
src/factory.hpp
src/UserInterface.hpp
src/ExecutionContext.hpp
)

# add_library(forth_lib STATIC ${SOURCES} ${HEADERS})

add_executable(forth ${SOURCES} ${HEADERS})


# target_compile_options(my_executable PRIVATE -fsanitize=address)
# target_link_libraries(my_executable PRIVATE -fsanitize=address)
