/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Button
*/

#pragma once

#include <openApp/Items/EventArea.hpp>
#include <openApp/Items/Rectangle.hpp>
#include <openApp/Items/Label.hpp>

namespace oA { class Button; }

class oA::Button : virtual public Rectangle, virtual public EventArea, virtual public Label
{
public:
    virtual ~Button(void) = default;

    virtual String getName(void) const noexcept { return "Button"; }

    virtual void onDraw(IRenderer &renderer) {
        Rectangle::onDraw(renderer);
        Label::onDraw(renderer);
    }
};