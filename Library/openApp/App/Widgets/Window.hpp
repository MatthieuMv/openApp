/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Window
*/

#pragma once

#include <openApp/App/Item.hpp>

namespace oA { class Window; }

class oA::Window : public Item
{
public:
    virtual ~Window(void) = default;

    Window(void) {
        append("title") = "openApp";
        append("color") = "white";
        append("resize") = true;
        append("fullscreen") = false;
        get("width") = 600;
        get("height") = 400;
    }

    virtual String getName(void) const noexcept { return "Window"; }

    virtual void onUpdate(IRenderer &renderer) {
        if (_index < 0)
            throw LogicError("Window", "Invalid use of unconfigured @Window@, openApp supports only Window as root item");
        if (get("resize"))
            pollWindow(renderer);
        else
            pushWindow(renderer);
    }

    WindowContext getWindowContext(void) const {
        return WindowContext(
            get("title")->getAs<Literal>(),
            V2i(get("x")->getAs<Number>(), get("y")->getAs<Number>()),
            V2i(get("width")->getAs<Number>(), get("height")->getAs<Number>()),
            oA::Color::RetreiveColor(get("color")->getAs<Literal>()),
            get("resize"),
            get("fullscreen")
        );
    }

    void setWindowIndex(Int index) { _index = index; }

private:
    Int _index = -1;

    void pushWindow(IRenderer &renderer) {
        WindowContext context;
        renderer.pollWindow(context);
        get("x") = context.pos.x;
        get("y") = context.pos.y;
        renderer.pushWindow(getWindowContext());
    }

    void pollWindow(IRenderer &renderer) {
        WindowContext context;
        renderer.pollWindow(context);
        get("x") = context.pos.x;
        get("y") = context.pos.y;
        get("width") = context.size.x;
        get("height") = context.size.y;
    }
};