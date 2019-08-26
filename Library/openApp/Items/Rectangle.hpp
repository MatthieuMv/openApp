/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Rectangle
*/

#pragma once

#include <openApp/Items/Item.hpp>
#include <openApp/Render/RenderContexts.hpp>

namespace oA { class Rectangle; }

class oA::Rectangle : virtual public Item
{
public:
    virtual ~Rectangle(void) = default;

    Rectangle(void) {
        append("color") = "black";
        append("fill") = true;
    }

    virtual String getName(void) const noexcept { return "Rectangle"; }

    virtual void onDraw(IRenderer &renderer) { renderer.draw(getRectangleContext()); }

    RectangleContext getRectangleContext(void) const {
        return RectangleContext(
            V2f(getAs<Number>("screenX"), getAs<Number>("screenY")),
            V2f(getAs<Number>("width"), getAs<Number>("height")),
            oA::Color::RetreiveColor(getAs<Literal>("color")),
            get("fill")
        );
    }
};