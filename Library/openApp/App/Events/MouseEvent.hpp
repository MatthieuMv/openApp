/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** MouseEvent
*/

#pragma once

#include <openApp/Types/V2.hpp>

namespace oA
{
    struct MouseEvent;
}

/**
 * @brief Data structure containing a mouse click event
 */
struct oA::MouseEvent
{
    enum EventType {
        Pressed,
        Released
    };

    enum KeyType {
        Left,
        Middle,
        Right,
        Button1,
        Button2
    };

    MouseEvent(void) = default;
    MouseEvent(EventType eventType, KeyType mouseKey, V2i mousePos, UInt eventTime) : type(eventType), key(mouseKey), pos(mousePos), timestamp(eventTime) {}

    EventType type = Pressed;
    KeyType key = Left;
    V2i pos; // Data containing a (x, y) pos
    UInt timestamp = 0;
};