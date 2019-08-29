/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** EventArea
*/

#pragma once

#include <openApp/Core/LightChrono.hpp>
#include <openApp/Items/Item.hpp>
#include <openApp/Render/RenderContexts.hpp>

namespace oA { class EventArea; }

class oA::EventArea : virtual public Item
{
public:
    virtual ~EventArea(void) = default;

    EventArea(void) {
        append("propagate") = true; // If true will propagate mouse clics
        append("pressed") = false; // Pressed state
        append("hovered") = false; // Hovered state
        append("released"); // Release event
        append("holded"); // Hold event
        append("holdDuration") = 500; // Pressed duration required to call holded event (in ms)
        append("doublePressed"); // Hold event
        append("doublePressInterval") = 500; // Press interval required to call doublePressed event (in ms)
    }

    virtual String getName(void) const noexcept { return "EventArea"; }

    virtual void onUpdate(IRenderer &) {
        if (get("pressed") && _hold.getMilliseconds() >= get("holdDuration").toUint()) {
            get("holded").emit();
            _hold.reset();
        }
    }

    virtual bool onEvent(const Event &event) {
        if (event.getType() == Event::Mouse)
            return handleMouseEvent(event.getAs<MouseEvent>());
        else if (event.getType() == Event::Motion)
            return handleMotionEvent(event.getAs<MotionEvent>());
        return false;
    }

private:
    LightChrono _hold, _double;

    bool handleMouseEvent(const MouseEvent &event) {
        auto &hovered = get("hovered") = contains(event.pos);
        get("pressed") = hovered && event.type == MouseEvent::Pressed;
        if (!hovered)
            return false;
        if (event.type != MouseEvent::Released) {
            _hold.reset();
            return !get("propagate");
        }
        get("released").call();
        if (_double.getMilliseconds() <= get("doublePressInterval").toUint())
            get("doublePressed").call();
        _double.reset();
        return !get("propagate");
    }

    bool handleMotionEvent(const MotionEvent &event) {
        bool hovered = contains(event.pos);
        get("hovered") = hovered;
        if (!hovered)
            get("pressed") = false;
        return false;
    }
};