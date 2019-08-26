/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** TilesetButton
*/

#pragma once

#include <openApp/Items/EventArea.hpp>
#include <openApp/Items/Label.hpp>
#include <openApp/Items/Tileset.hpp>

namespace oA { class TilesetButton; }

class oA::TilesetButton : virtual public Tileset, virtual public EventArea, virtual public Label
{
public:
    virtual ~TilesetButton(void) = default;

    virtual String getName(void) const noexcept { return "TilesetButton"; }

    virtual void onDraw(IRenderer &renderer) {
        Tileset::onDraw(renderer);
        Label::onDraw(renderer);
    }
};