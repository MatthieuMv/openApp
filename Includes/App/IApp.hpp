/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IApp
*/

#pragma once

// IRenderer
#include "App/IRenderer.hpp"

namespace oA { class IApp; }

class oA::IApp
{
public:
    virtual ~IApp(void) {}

    virtual void run(void) = 0;
};