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

    /* Virtual 3D Scene functions :
        clearScene() : destroy current context' scene
        drawScene() : draw current context' scene
    */
    virtual void clearScene(void) = 0;
    virtual void drawScene(void) = 0;

    /* Supported node objects */
    virtual Uint addCube(const CubeContext &ctx) = 0;
    virtual Uint addCamera(const CameraContext &ctx) = 0;
    virtual Uint addModel(const ModelContext &ctx) = 0;
    virtual Uint addAnimatedModel(const ModelContext &ctx) = 0;

    /* Node API */
    virtual void removeSceneNode(oA::Uint node) = 0;
    virtual void moveNode(oA::Uint node, const oA::V3f &move) = 0;
    virtual void setNodePosition(oA::Uint node, const oA::V3f &position) = 0;
    virtual void setNodeRotation(oA::Uint node, const oA::V3f &rotation) = 0;
    virtual void setNodeScale(oA::Uint node, const oA::V3f &scale) = 0;
    virtual void setNodeAnimation(oA::Uint node, oA::Uint from, oA::Uint to, oA::Uint speed, bool loop) = 0;
    virtual oA::V3f getNodePosition(oA::Uint node) const = 0;
    virtual oA::V3f getNodeRotation(oA::Uint node) const = 0;
    virtual oA::V3f getNodeScale(oA::Uint node) const = 0;
};