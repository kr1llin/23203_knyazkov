cmake_minimum_required(VERSION 3.10)  
project(SpaceInvaders)                      

set(SANITIZER_FLAGS "-fsanitize=address")
find_package(SFML COMPONENTS graphics window system REQUIRED)

set(Sources main.cpp Draw.cpp Engine.cpp Input.cpp Player.cpp Update.cpp Alien.cpp Invaders.cpp Level.cpp StateManager.cpp)
set(Header Draw.hpp Engine.hpp Input.hpp Player.hpp Update.hpp Alien.hpp Invaders.hpp Level.hpp State.hpp StateManager.hpp)

add_executable(SpaceInvaders ${Sources})

target_link_libraries(SpaceInvaders sfml-graphics sfml-window sfml-system)


# set(wxWidgets_ROOT_DIR /usr/local/include/wx-3.2) 

# find_package(wxWidgets REQUIRED COMPONENTS core base) 

# include(${wxWidgets_USE_FILE})

# set(SOURCES
#     main.cpp  
# )

# add_executable(MyWxApp ${SOURCES})

# target_link_libraries(MyWxApp ${wxWidgets_LIBRARIES})
