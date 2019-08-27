cmake_minimum_required(VERSION 3.0.0)
project(openApp)

set(oAPath .)

set(oARendererTarget "SDL")

include(Renderer.cmake)

if (${oARendererTarget} STREQUAL "SDL")
    message(" | Compiling openApp with SDL Renderer |")
    find_package(SDL2 REQUIRED)
    set(oARendererSources ${oASDLRenderer})
else ()
    message(FATAL_ERROR " | ! Can't compile openApp without renderer ! |")
endif ()


if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -g3")
endif ()

set(CMAKE_CXX_STANDARD 17)

#add_executable(openApp ${oASources} ${oARendererSources} Main.cpp)
add_library(openApp SHARED ${oASources} ${oARendererSources})

target_include_directories(openApp
    PRIVATE ${oAPath}
)

target_link_libraries(openApp
    SDL2
    SDL2_image
    SDL2_ttf
)
