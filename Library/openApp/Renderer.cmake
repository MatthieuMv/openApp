cmake_minimum_required(VERSION 3.0.0)
project(openApp)

# This file need variables 'oALibraryDir' and 'oARendererTarget' to be set !

include(openApp.cmake)

set(oASDL ${oARender}/SDL)

set(oASDLRenderer
    ${oASDL}/SDLRenderer.hpp
    ${oASDL}/SDLRenderer.cpp
    ${oASDL}/Extern/SDL_FontCache.h
    ${oASDL}/Extern/SDL_FontCache.c
    ${oASDL}/Extern/SDL2_gfxPrimitives.h
    ${oASDL}/Extern/SDL2_gfxPrimitives.c
    ${oASDL}/Extern/SDL2_gfxPrimitives_font.h
    ${oASDL}/Extern/SDL2_rotozoom.h
    ${oASDL}/Extern/SDL2_rotozoom.c
    ${oARoot}/SDLApp.hpp
)