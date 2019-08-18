/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Window
*/

#pragma once

#include <openApp/App/Item.hpp>

namespace oA { class Window; }

class oA::Window : virtual public Item
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
        if (getWindowIndex() < 0)
            throw LogicError("Window", "Invalid use of unconfigured @Window@, openApp supports only Window as root item");
        if (get("resize")) {
            renderer.setWindowResizable(getWindowIndex(), true);
            auto size = renderer.getWindowSize(getWindowIndex());
            get("width") = size.x; get("height") = size.y;
        } else
            renderer.setWindowResizable(getWindowIndex(), false);
        auto pos = renderer.getWindowPos(getWindowIndex());
        get("x") = pos.x; get("y") = pos.y;
        renderer.setWindowColor(getWindowIndex(), Color::RetreiveColor(getAs<Literal>("color")));
    }

    WindowContext getWindowContext(void) const {
        return WindowContext(
            getAs<Literal>("title"),
            V2i(getAs<Number>("screenX"), getAs<Number>("screenY")),
            V2i(getAs<Number>("width"), getAs<Number>("height")),
            oA::Color::RetreiveColor(getAs<Literal>("color")),
            get("resize"),
            get("fullscreen")
        );
    }

    void setWindowIndex(Int index) { _index = index; }

    Int getWindowIndex(void) const noexcept { return _index; }

private:
    Int _index = -1;
};