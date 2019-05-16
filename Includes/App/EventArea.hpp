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
        append("hoverEnabled") = false;
        append("hovered") = false;
        append("focusEnabled") = false;
        append("focused") = false;
    }

    virtual ~EventArea(void) {}

    virtual String getName(void) const noexcept { return "EventArea"; }
};
