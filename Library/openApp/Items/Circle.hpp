/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Circle
*/

#pragma once

#include <openApp/Items/Item.hpp>
#include <openApp/Render/RenderContexts.hpp>

namespace oA { class Circle; }

class oA::Circle : virtual public Item
{
public:
    virtual ~Circle(void) = default;

    Circle(void) {
        append("color") = "black";
        append("fill") = true;
        append("size") = 0;
        append("antialiasing") = false;
    }

    virtual String getName(void) const noexcept { return "Circle"; }

    virtual void onDraw(IRenderer &renderer) { renderer.draw(getCircleContext()); }

    CircleContext getCircleContext(void) const {
        auto ctx = CircleContext(
            V2f(getAs<Number>("screenX") + getAs<Number>("width") / 2.0f, getAs<Number>("screenY") + getAs<Number>("height") / 2.0f),
            getAs<Number>("size"),
            oA::Color::RetreiveColor(getAs<Literal>("color")),
            get("fill"),
            get("antialiasing")
        );
        return ctx;
    }
};