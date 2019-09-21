/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Event
*/

#pragma once

#include <openApp/Types/Variant.hpp>
#include <openApp/App/Events/WindowEvent.hpp>
#include <openApp/App/Events/MouseEvent.hpp>
#include <openApp/App/Events/MotionEvent.hpp>
#include <openApp/App/Events/WheelEvent.hpp>
#include <openApp/App/Events/KeyboardEvent.hpp>
#include <openApp/App/Events/DropEvent.hpp>
#include <openApp/App/Events/TextEvent.hpp>

namespace oA { struct Event; }

struct oA::Event : public Variant<WindowEvent, MouseEvent, MotionEvent, WheelEvent, KeyboardEvent, TextEvent, DropEvent>
{
    enum EventType {
        Window,
        Mouse,
        Motion,
        Wheel,
        Keyboard,
        Text,
        Drop
    };

    Int window = -1;

    EventType getType(void) const noexcept { return static_cast<EventType>(index()); }

    template<typename T>
    const T &getAs(void) const { return std::get<T>(*this); }
};