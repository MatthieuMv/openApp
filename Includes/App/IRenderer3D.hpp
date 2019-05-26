/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IRenderer3D
*/

#pragma once

// IRenderer
#include "App/IRenderer.hpp"
// 3D Contexts
#include "App/Context3D.hpp"

namespace oA
{
    class IRenderer3D;
}

class oA::IRenderer3D : public IRenderer
{
public:
    virtual ~IRenderer3D(void) = default;

    /* Virtual 3D Scene functions */
    virtual void clearScene(Uint index = 0) = 0;
    virtual void addCube(const CubeContext &ctx, Uint index = 0) = 0;
    virtual void addCamera(const CameraContext &ctx, Uint index = 0) = 0;
    virtual void drawScene(oA::Uint index = 0) = 0;
};