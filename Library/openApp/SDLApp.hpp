/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** SDLApp
*/

#pragma once

#include <openApp/App/App.hpp>
#include <openApp/Render/SDL/SDLRenderer.hpp>

namespace oA { class SDLApp; }

class oA::SDLApp : public App
{
public:
    virtual ~SDLApp(void) = default;

    SDLApp(void) : App(std::make_unique<SDLRenderer>()) {}
};