/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** WindowEvent
*/

#pragma once

#include <openApp/Types/V2.hpp>

namespace oA
{
    struct WindowEvent;
}

/**
 * @brief Data structure containing a window event
 */
struct oA::WindowEvent
{
    enum EventType {
        Shown,
        Hidden,
        Moved,
        Resized,
        Minimized,
        Maximized,
        Restored,
        MouseEnter,
        MouseLeave,
        KeyboardFocus,
        KeyboardLostFocus,
        Close
    };

    WindowEvent(void) = default;
    WindowEvent(EventType eventType, const V2i &windowData, Uint eventTime) : type(eventType), data(windowData), timestamp(eventTime) {}

    EventType type = Shown;
    V2i data; // Data containing either a (x,y) coord or a (width,height) size
    Uint timestamp = 0;
};