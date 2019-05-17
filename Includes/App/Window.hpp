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
        get("width") = 720;
        get("height") = 480;
    }

    virtual ~Window(void) {}

    virtual String getName(void) const noexcept { return "Window"; }

    virtual void draw(IRenderer &renderer) {
        if (*get("resizable")) {
            WindowContext ctx;
            renderer.pullWindow(ctx);
            get("width") = ctx.width;
            get("height") = ctx.height;
        }
        Rectangle::draw(renderer);
    }

    void getWindowContext(WindowContext &ctx) const {
        ctx.width = get("width")->toInt();
        ctx.height = get("height")->toInt();
        ctx.resizable = *get("resizable");
    }
};