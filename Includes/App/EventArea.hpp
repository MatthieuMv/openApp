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
        auto &focused = append("focused");
        focused = false;
        focused.connect([this, &focused]{
            if (*focused)
                onFocused();
            else
                onDefocused();
            return true;
        });
        append("pressed") = false;
        append("hovered") = false;
        append("released"); // Released signal
    }

    virtual ~EventArea(void) {}

    virtual String getName(void) const noexcept { return "EventArea"; }

    /* Override these functions to add custom events behaviors */
    virtual bool onEvent(Event &evt) override {
        if (evt.type() == Mouse)
            return onMouse(evt.mouse());
        else if (evt.type() == Keyboard)
            return onKeyboard(evt.keyboard());
        return false;
    }

    virtual bool onMouse(MouseEvent &evt) {
        auto &pressed = get("pressed");
        if (contains(evt.pos)) {
            get("hovered") = true;
            if (evt.state == MousePressed) {
                pressed = true;
                onPressed();
            } else if (*pressed && evt.state == MouseReleased) {
                pressed = false;
                get("released").emit();
                onReleased();
                get("focused") = true;
            }
        } else {
            get("hovered") = false;
            pressed = false;
            if (evt.state != MouseMove)
                get("focused") = false;
        }
        return false;
    }

    virtual bool onKeyboard(KeyboardEvent &) { return false; }

    virtual void onPressed(void) {}
    virtual void onReleased(void) {}
    virtual void onFocused(void) {}
    virtual void onDefocused(void) {}
};
