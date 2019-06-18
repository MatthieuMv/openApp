cmake_minimum_required(VERSION 3.0.0)
project(openApp)

set(oAPath .)

include(openApp.cmake)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -std=c++17 -fPIC -g3")
endif ()

include_directories(${oAPath})

#add_library(openApp ${oASources})
add_executable(openApp ${oASources} Main.cpp)