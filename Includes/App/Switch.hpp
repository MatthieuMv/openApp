/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Switch
*/

#pragma once

// Rectangle
#include "App/Button.hpp"

namespace oA { class Switch; }

class oA::Switch : virtual public Button
{
public:
    Switch(void) {
        append("state") = false;
        append("circleColor") = "darkgrey";
        get("color") = "lightgrey";
        get("hCenter") = true;
        get("vCenter") = false;
    }

    virtual ~Switch(void) {}

    virtual String getName(void) const noexcept { return "Switch"; }

    virtual void draw(IRenderer &renderer) {
        RectangleContext rect;
        CircleContext circle;
        TextContext text;
        getBarContext(rect);
        getCircleContext(circle);
        getSwitchTextContext(text);
        renderer.drawRectangle(rect);
        renderer.drawCircle(circle);
        renderer.drawText(text);
    }

    virtual void onReleased(void) {
        auto &s = get("state");
        s = !*s;
    }

private:
    void getBarContext(RectangleContext &ctx) const {
        getRectangleContext(ctx);
        auto height = ctx.height / 4;
        ctx.y += ctx.height / 2 - height / 2;
        ctx.height = height;
    }

    void getCircleContext(CircleContext &ctx) const {
        auto x = get("screenX")->getConst<Float>();
        auto y = get("screenY")->getConst<Float>();
        auto w = get("width")->getConst<Float>();
        auto h = get("height")->getConst<Float>();
        auto r = h / 3;
        bool active = *get("state");
        ctx.x = active ? x + w - r : x + r;
        ctx.y = y + h / 2;
        ctx.radius = r;
        ctx.color = Color::RetreiveColor(get("circleColor")->getConst<String>());
    }

    void getSwitchTextContext(TextContext &ctx) const {
        getTextContext(ctx);
        ctx.y += ctx.height;
        ctx.height /= 2;
    }
};