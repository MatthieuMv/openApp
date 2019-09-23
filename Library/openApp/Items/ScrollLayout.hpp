/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ScrollLayout
*/

#pragma once

#include <openApp/Items/Layout.hpp>
#include <openApp/Items/EventArea.hpp>
#include <openApp/Core/Log.hpp>

namespace oA { class ScrollLayout; }

class oA::ScrollLayout : virtual public Layout, virtual public EventArea
{
public:
    virtual ~ScrollLayout(void) = default;

    ScrollLayout(void) {
        append("horizontalScroll") = false;
        append("verticalScroll") = false;
        append("scrollX") = 0.0f;
        append("scrollY") = 0.0f;
        append("scrollMinX") = 0.0f;
        append("scrollMinY") = 0.0f;
        append("scrollMaxX") = 0.0f;
        append("scrollMaxY") = 0.0f;
        setExpression("deltaX", "scrollX");
        setExpression("deltaY", "scrollY");
    }

    virtual String getName(void) const noexcept { return "ScrollLayout"; }

    virtual bool onEvent(IRenderer &renderer, const Event &event) {
        bool res = EventArea::onEvent(renderer, event);
        if (!get("hovered"))
            return false;
        switch (event.getType()) {
        case Event::Wheel:
            return handleWheelEvent(event.getAs<WheelEvent>());
        case Event::Motion:
            return handleMotionEvent(event.getAs<MotionEvent>());
        default:
            return res;
        }
    }

private:
    bool handleWheelEvent(const WheelEvent &event) {
        bool used = false;
        if (event.scroll.x && get("horizontalScroll")) {
            updateScroll(get("scrollX"), get("scrollMinX"), get("scrollMaxX"), event.scroll.x * getAs<Number>("width") * 0.05);
            used = true;
        }
        if (event.scroll.y && get("verticalScroll")) {
            updateScroll(get("scrollY"), get("scrollMinY"), get("scrollMaxY"), event.scroll.y * getAs<Number>("height") * 0.05);
            used = true;
        }
        return used;
    }

    bool handleMotionEvent(const MotionEvent &event) {
        bool used = false;
        if (!get("pressed"))
            return false;
        if (event.speed.x && get("horizontalScroll")) {
            updateScroll(get("scrollX"), get("scrollMinX"), get("scrollMaxX"), event.speed.x);
            used = true;
        }
        if (event.speed.y && get("verticalScroll")) {
            updateScroll(get("scrollY"), get("scrollMinY"), get("scrollMaxY"), event.speed.y);
            used = true;
        }
        return used;
    }

    void updateScroll(Var &value, const Var &min, const Var &max, Var &&delta) {
        delta += value;
        if (delta > max)
            value = max;
        else if (delta < min)
            value = min;
        else
            value = delta;
    }
};
