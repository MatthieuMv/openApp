/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** WheelEvent
*/

#pragma once

#include <openApp/Types/V2.hpp>

namespace oA
{
    struct WheelEvent;
}

/**
 * @brief Data structure containing a mouse motion event
 */
struct oA::WheelEvent
{
    enum Direction {
        Top,
        Bottom
    };

    WheelEvent(void) = default;
    WheelEvent(Direction wheelDirection, const V2i &scrollDistance, UInt eventTime) : direction(wheelDirection), scroll(scrollDistance), timestamp(eventTime) {}

    Direction direction = Top;
    V2i scroll; // Scroll amount (x, y)
    UInt timestamp = 0;
};