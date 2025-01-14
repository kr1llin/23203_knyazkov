cmake_minimum_required(VERSION 3.10)  
project(SpaceInvaders)                      

set(SANITIZER_FLAGS "-fsanitize=address")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

find_package(SFML COMPONENTS graphics window system REQUIRED)

set(Sources main.cpp Draw.cpp Engine.cpp Input.cpp Player.cpp Update.cpp Alien.cpp Invaders.cpp Level.cpp StateManager.cpp Bullet.cpp GameOver.cpp)
set(Header Draw.hpp Engine.hpp Input.hpp Player.hpp Update.hpp Alien.hpp Invaders.hpp Level.hpp State.hpp StateManager.hpp Bullet.hpp CollisionInterface.hpp)

add_executable(SpaceInvaders ${Sources})

target_link_libraries(SpaceInvaders sfml-graphics sfml-window sfml-system)

