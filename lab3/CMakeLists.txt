cmake_minimum_required(VERSION 3.10)  
project(SpaceInvaders)                      

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(SANITIZER_FLAGS "-fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZER_FLAGS}")

find_package(SFML COMPONENTS graphics window system REQUIRED)

file(GLOB Sources "*.cpp")
file(GLOB Header "*.hpp")
add_executable(SpaceInvaders ${Sources})

target_compile_options(SpaceInvaders PRIVATE ${SANITIZER_FLAGS})
target_link_libraries(SpaceInvaders sfml-graphics sfml-window sfml-system)

