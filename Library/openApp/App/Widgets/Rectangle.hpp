/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Rectangle
*/

#pragma once

#include <openApp/App/Item.hpp>
#include <openApp/App/RenderContexts.hpp>

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
            V2f(get("screenX")->getAs<Number>(), get("screenY")->getAs<Number>()),
            V2f(get("width")->getAs<Number>(), get("height")->getAs<Number>()),
            oA::Color::RetreiveColor(get("color")->getAs<Literal>()),
            get("fill")
        );
    }
};