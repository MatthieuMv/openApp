/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ImageButton
*/

#pragma once

#include <openApp/App/Widgets/EventArea.hpp>
#include <openApp/App/Widgets/Image.hpp>

namespace oA { class ImageButton; }

class oA::ImageButton : virtual public Image, virtual public EventArea
{
public:
    virtual ~ImageButton(void) = default;

    virtual String getName(void) const noexcept { return "ImageButton"; }
};