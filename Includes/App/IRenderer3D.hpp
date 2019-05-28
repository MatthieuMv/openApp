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
// 3D Animations
#include "App/Animation3D.hpp"

namespace oA
{
    class IRenderer3D;
}

class oA::IRenderer3D : public IRenderer
{
public:
    virtual ~IRenderer3D(void) = default;

    /* Virtual 3D Scene functions :
        clearScene() : destroy current context' scene
        drawScene() : draw current context' scene
        addXYZ() : add a node to the scene, and return its index
    */
    virtual void clearScene(void) = 0;
    virtual void drawScene(void) = 0;
    virtual Uint addCube(const CubeContext &ctx) = 0;
    virtual Uint addCamera(const CameraContext &ctx) = 0;
    virtual Uint addModel(const ModelContext &ctx) = 0;
    virtual Uint addAnimatedModel(const ModelContext &ctx) = 0;
    virtual void applyAnimation(oA::Uint node, const Animation3D &anim) = 0;
};