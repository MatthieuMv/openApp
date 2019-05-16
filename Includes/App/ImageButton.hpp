/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ImageButton
*/

#pragma once

// Image
#include "App/Image.hpp"
// Button
#include "App/Button.hpp"

namespace oA { class ImageButton; }

class oA::ImageButton : virtual public oA::Button, virtual public oA::Image
{
public:
    ImageButton(void) {}

    virtual ~ImageButton(void) {}

    virtual String getName(void) const noexcept { return "ImageButton"; }

    virtual void draw(IRenderer &renderer) {
        Image::draw(renderer);
        Text::draw(renderer);
    }
};
