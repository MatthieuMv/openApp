/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Motion
*/

#pragma once

#include <openApp/Types/V2.hpp>

namespace oA
{
    struct MotionEvent;
}

/**
 * @brief Data structure containing a mouse motion event
 */
struct oA::MotionEvent
{
    MotionEvent(void) = default;
    MotionEvent(const V2i &mousePos, const V2i &mouseSpeed, UInt eventTime) : pos(mousePos), speed(mouseSpeed), timestamp(eventTime) {}

    V2i pos; // Mouse position
    V2i speed; // Mouse speed
    UInt timestamp = 0;
};