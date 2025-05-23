cmake_minimum_required(VERSION 3.5)

project(TestCoverage)

add_definitions(-fprofile-arcs -ftest-coverage)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/TestCoverage.dir/src)
message("-- Object files will be output to: ${OBJECT_DIR}")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(src/googletest)

include_directories(../)

include_directories(/usr/include)
link_directories(/usr/lib)

set(GTEST_VERBOSE 1 CACHE BOOL "Enable verbose output for Google Test")


set(SOURCES
    src/all_tests.cc
    # ../src/main.cpp
    ../src/forth.cpp
../src/scanner.cpp
../src/interpreter.cpp
../src/expressions.cpp
../src/factory.cpp
../src/UserInterface.cpp
../src/ExecutionContext.cpp
    )

# set(HEADERS
# ../src/forth.hpp
# ../src/scanner.hpp
# ../src/Token.hpp
# ../src/interpreter.hpp
# ../src/expressions.hpp
# ../src/factory.hpp
# ../src/UserInterface.hpp
# ../src/ExecutionContext.hpp
# )

    include_directories(
        src/
        ../src/
        )

# Add the forth library
# add_library(forth_lib STATIC
#     ../forth.cpp
#     ../scanner.cpp
#     ../interpreter.cpp
#     ../expressions.cpp
#     ../factory.cpp
#     ../UserInterface.cpp
#     ../ExecutionContext.cpp
# )

# Add the test executable
add_executable(TestCoverage ${SOURCES})


# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p gcoverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${SOURCES} -o ${OBJECT_DIR}
    COMMAND echo "-- Source directory: ${CMAKE_SOURCE_DIR}/src/"
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/gcoverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gcoverage
    )
add_dependencies(gcov TestCoverage)

# Create the lcov target. Run result tests with 'make lcov'
add_custom_target(lcov
    COMMAND mkdir -p lcoverage
    )
add_custom_command(TARGET lcov
    COMMAND echo "=================== LCOV ===================="
    COMMAND echo "-- Passing lcov tool under code coverage"
    COMMAND lcov --capture --directory ../ --output-file lcoverage/main_coverage.info --ignore-errors mismatch
    COMMAND echo "-- Generating HTML output files"
    COMMAND genhtml lcoverage/main_coverage.info --output-directory lcoverage --ignore-errors mismatch
    )

# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES gcoverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files.
add_custom_target(init
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Testing
enable_testing()
# add_test(NAME output_test COMMAND output_test)
add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/TestCoverage)
# add_test(NAME output_test COMMAND output_test --gtest_verbose=1)


# link Boost libraries to the new target
target_link_libraries(TestCoverage )
target_link_libraries(TestCoverage gtest)
target_link_libraries(TestCoverage gmock)
target_link_libraries(TestCoverage pthread)
target_link_libraries(TestCoverage -fprofile-arcs)

# Link the Google Test libraries and the forth library to the test executable
# target_link_libraries(TestCoverage gtest_main gmock_main forth_lib)

# Enable testing for the test executable
# add_test(NAME ForthTests COMMAND TestCoverage)
