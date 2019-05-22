/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Event
*/

#pragma once

// Scalar types
#include "Core/Scalar.hpp"
// V2f
#include "Core/V2.hpp"
// Variant
#include "Core/Variant.hpp"
// Shared
#include "Core/Memory.hpp"
// LogicError
#include "Core/Error.hpp"
// Keys
#include "App/Keys.hpp"

namespace oA
{
    struct MouseEvent;
    struct KeyboardEvent;
    struct Event;

    enum EventType {
        NullEvent = 0,
        Mouse,
        Keyboard
    };
}

struct oA::MouseEvent
{
    V2f pos;
    Float wheel = 0;
    MouseKey key = MouseNull;
    MouseState state = MousePressed;
    bool shift = false, control = false;
};

struct oA::KeyboardEvent
{
    Key key = KeyNull;
    KeyState state = KeyPressed;
    bool shift = false, control = false;

    char convetToKey(void) const noexcept;
};

class oA::Event
{
public:
    EventType type(void) const noexcept { return _type; }
    void setType(EventType value) noexcept { _type = value; }

    void initAsMouse(void) noexcept { _var = MouseEvent(); }
    void initAsKeyboard(void) noexcept { _var = KeyboardEvent(); }

    MouseEvent &mouse(void) {
        try { return std::get<MouseEvent>(_var); }
        catch (...) { throw LogicError("Event", "Event is not a @MouseEvent@"); }
    }

    const MouseEvent &mouse(void) const {
        try { return std::get<MouseEvent>(_var); }
        catch (...) { throw LogicError("Event", "Event is not a @MouseEvent@"); }
    }

    KeyboardEvent &keyboard(void) {
        try { return std::get<KeyboardEvent>(_var); }
        catch (...) { throw LogicError("Event", "Event is not a @KeyboardEvent@"); }
    }

    const KeyboardEvent &keyboard(void) const {
        try { return std::get<KeyboardEvent>(_var); }
        catch (...) { throw LogicError("Event", "Event is not a @KeyboardEvent@"); }
    }

private:
    EventType _type = NullEvent;
    Variant<MouseEvent, KeyboardEvent> _var;
};