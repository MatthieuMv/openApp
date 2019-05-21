/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Scene3D
*/

#pragma once

// Item
#include "App/Item.hpp"
// IRenderer3D
#include "App/IRenderer3D.hpp"
// 3D Contexts
#include "App/Context3D.hpp"


namespace oA { class Scene3D; }

class oA::Scene3D : virtual public oA::Item
{
public:
    Scene3D(void) {}

    virtual ~Scene3D(void) {}

    virtual String getName(void) const noexcept { return "Scene3D"; }

    virtual void draw(IRenderer &renderer) {
        if (!renderer.supports3D())
            throw LogicError("Scene3D", "Given @renderer@ doesn't support 3D");
        draw3D(dynamic_cast<IRenderer3D &>(renderer));
    }

    // Override to draw your scene
    virtual void draw3D(IRenderer3D &) {}

};