cmake_minimum_required(VERSION 3.0.0)
project(openApp VERSION 1.0.0)

set(oAPath ..)

include(../openApp.cmake)

set(TestsSources
    tests_Error.cpp
    tests_String.cpp
    tests_ContainerHelper.cpp
)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -std=c++17 -lcriterion --coverage")
include_directories(${oAPath})

add_executable(run_tests ${TestsSources} ${oASources})
