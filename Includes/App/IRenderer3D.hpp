/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IRenderer3D
*/

#pragma once

// IRenderer
#include "App/IRenderer.hpp"

namespace oA
{
    class IRenderer3D;
}

class oA::IRenderer3D : public IRenderer
{
public:
    virtual ~IRenderer3D(void) = default;
};