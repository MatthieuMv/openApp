/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** TextEvent
*/

#pragma once

#include <openApp/Types/V2.hpp>

namespace oA
{
    struct TextEvent;
}

/**
 * @brief Data structure containing a mouse click event
 */
struct oA::TextEvent
{
    TextEvent(void) = default;
    TextEvent(String &&eventText, UInt eventTime) : input(std::move(eventText)), timestamp(eventTime) {}

    String input;
    UInt timestamp = 0;
};