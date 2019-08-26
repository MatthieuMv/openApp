/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** AnimatedTileButton
*/

#pragma once

#include <openApp/Items/EventArea.hpp>
#include <openApp/Items/Label.hpp>
#include <openApp/Items/AnimatedTile.hpp>

namespace oA { class AnimatedTileButton; }

class oA::AnimatedTileButton : virtual public AnimatedTile, virtual public EventArea, virtual public Label
{
public:
    virtual ~AnimatedTileButton(void) = default;

    virtual String getName(void) const noexcept { return "AnimatedTileButton"; }

    virtual void onUpdate(IRenderer &renderer) {
        AnimatedTile::onUpdate(renderer);
        EventArea::onUpdate(renderer);
    }

    virtual void onDraw(IRenderer &renderer) {
        AnimatedTile::onDraw(renderer);
        Label::onDraw(renderer);
    }
};