/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ImageButton
*/

#pragma once

#include <openApp/App/Items/EventArea.hpp>
#include <openApp/App/Items/Image.hpp>
#include <openApp/App/Items/Label.hpp>

namespace oA { class ImageButton; }

class oA::ImageButton : virtual public Image, virtual public EventArea, virtual public Label
{
public:
    virtual ~ImageButton(void) = default;

    virtual String getName(void) const noexcept { return "ImageButton"; }

    virtual void onDraw(IRenderer &renderer) {
        Image::onDraw(renderer);
        Label::onDraw(renderer);
    }
};