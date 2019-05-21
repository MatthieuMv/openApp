/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Button
*/

#pragma once

// Rectangle
#include "App/Rectangle.hpp"
// Text
#include "App/Text.hpp"
// EventArea
#include "App/EventArea.hpp"

namespace oA { class Button; }

class oA::Button : virtual public oA::Rectangle, virtual public oA::Text, virtual public oA::EventArea
{
public:
    Button(void) {
        get("hCenter") = true;
        get("vCenter") = true;
    }

    virtual ~Button(void) {}

    virtual String getName(void) const noexcept { return "Button"; }

    virtual void draw(IRenderer &renderer) {
        Rectangle::draw(renderer);
        Text::draw(renderer);
    }
};
