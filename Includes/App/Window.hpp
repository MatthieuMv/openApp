/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Window
*/

#pragma once

// Rectangle
#include "App/Rectangle.hpp"

namespace oA { class Window; }

class oA::Window : virtual public oA::Rectangle
{
public:
    Window(void) {
        append("resizable") = false;
        append("title") = "openApp";
        get("width") = 720;
        get("height") = 480;
    }

    virtual ~Window(void) {}

    virtual String getName(void) const noexcept { return "Window"; }

    virtual void draw(IRenderer &renderer) {
        if (*get("resizable")) {
            WindowContext ctx;
            renderer.pullWindow(ctx);
            get("width") = ctx.size.x;
            get("height") = ctx.size.y;
        }
        Rectangle::draw(renderer);
    }

    void getWindowContext(WindowContext &ctx) const {
        ctx.size.x = get("width")->toInt();
        ctx.size.y = get("height")->toInt();
        ctx.resizable = *get("resizable");
        ctx.title = get("title")->getConst<String>();
    }
};