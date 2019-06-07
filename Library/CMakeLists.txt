cmake_minimum_required(VERSION 3.0.0)
project(openApp)

set(oAPath .)

include(openApp.cmake)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -std=c++17 -fPIC")
include_directories(${oAPath})

add_library(openApp ${oASources})