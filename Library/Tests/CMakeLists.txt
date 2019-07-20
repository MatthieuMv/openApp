cmake_minimum_required(VERSION 3.0.0)
project(openApp VERSION 1.0.0)

set(oAPath ..)

include(../openApp.cmake)

set(TestsSources
    tests_Error.cpp
    tests_String.cpp
    tests_ContainerHelper.cpp
    tests_Log.cpp
    tests_V2.cpp
    tests_V3.cpp
    tests_Color.cpp
    tests_Chrono.cpp
    tests_Path.cpp
    tests_Signal.cpp
    tests_Property.cpp
    tests_Expression.cpp
    tests_ExpressionHandler.cpp
    tests_Var.cpp
    tests_Item.cpp
    tests_ItemHandler.cpp
    tests_ItemFactory.cpp
    tests_GetLine.cpp
    tests_OALexer.cpp
    tests_OAParser.cpp
)

set(CMAKE_CXX_STANDARD 17)


if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -coverage")
endif ()

link_libraries(criterion)

include_directories(${oAPath})

add_executable(run_tests ${TestsSources} ${oASources})