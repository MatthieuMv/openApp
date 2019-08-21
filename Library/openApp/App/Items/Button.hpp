/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Button
*/

#pragma once

#include <openApp/App/Items/EventArea.hpp>
#include <openApp/App/Items/Rectangle.hpp>
#include <openApp/App/Items/Label.hpp>

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