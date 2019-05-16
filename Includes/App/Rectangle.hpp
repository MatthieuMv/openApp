/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Rectangle
*/

#pragma once

// Item
#include "App/Item.hpp"

namespace oA { class Rectangle; }

class oA::Rectangle : virtual public Item
{
public:
    Rectangle(void) {
        append("color") = "black";
    }

    virtual ~Rectangle(void) {}

    virtual String getName(void) const noexcept { return "Rectangle"; }

    virtual void draw(IRenderer &renderer) {
        RectangleContext ctx;
        getRectangleContext(ctx);
        renderer.drawRectangle(ctx);
    }

    void getRectangleContext(RectangleContext &ctx) const {
        getItemContext(ctx);
        ctx.color = Color::RetreiveColor(get("color")->getConst<String>());
    }
};