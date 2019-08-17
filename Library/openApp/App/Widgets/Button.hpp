/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Button
*/

#pragma once

#include <openApp/App/Widgets/EventArea.hpp>
#include <openApp/App/Widgets/Rectangle.hpp>

namespace oA { class Button; }

class oA::Button : virtual public Rectangle, virtual public EventArea
{
public:
    virtual ~Button(void) = default;

    virtual String getName(void) const noexcept { return "Button"; }
};