cmake_minimum_required(VERSION 3.0.0)
project(openAudio)

set(oAPath ../)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -g3")
endif ()

set(CMAKE_CXX_STANDARD 17)

set(oASources
    Audio.hpp
    Audio.cpp
    Voice.hpp
    Voice.cpp
)

add_executable(openAudio ${oASources} Main.cpp)
#add_library(openAudio SHARED ${oASources})

target_include_directories(openAudio
    PRIVATE ${oAPath}
)

target_link_directories(openAudio
    PRIVATE ${oAPath}
)

target_link_libraries(openAudio
    openApp
    SDL2
)
