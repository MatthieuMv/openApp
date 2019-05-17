/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** EventArea
*/

#pragma once

// Item
#include "App/Item.hpp"

namespace oA { class EventArea; }

class oA::EventArea : virtual public oA::Item
{
public:
    EventArea(void) {
        append("pressed") = false;
        append("hovered") = false;
        append("focused") = false;
    }

    virtual ~EventArea(void) {}

    virtual String getName(void) const noexcept { return "EventArea"; }

    virtual bool onEvent(Event &evt) override {
        if (evt.type() == Mouse)
            return onMouse(evt.mouse());
        else if (evt.type() == Keyboard)
            return onKeyboard(evt.keyboard());
        return false;
    }

    virtual bool onMouse(MouseEvent &evt) {
        if (contains(evt.x, evt.y)) {
            get("hovered") = true;
            if (evt.state == MousePressed)
                get("pressed") = true;
            if (evt.state == MouseReleased) {
                get("pressed") = false;
                get("focused") = true;
            }
            return true;
        } else {
            get("hovered") = false;
            get("pressed") = false;
            if (*get("focused") && evt.state == MousePressed)
                get("focused") = false;
        }
        return false;
    }

    virtual bool onKeyboard(KeyboardEvent &) {
        return false;
    }
};
