cmake_minimum_required(VERSION 3.10)  
project(MyWxApp)                      

set(wxWidgets_ROOT_DIR /usr/local/include/wx-3.2) 

find_package(wxWidgets REQUIRED COMPONENTS core base) 

include(${wxWidgets_USE_FILE})

set(SOURCES
    main.cpp  
)

add_executable(MyWxApp ${SOURCES})

target_link_libraries(MyWxApp ${wxWidgets_LIBRARIES})
