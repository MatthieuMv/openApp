/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** AnimatedTile
*/

#pragma once

#include <openApp/Items/Tileset.hpp>
#include <openApp/Items/Timer.hpp>

namespace oA { class AnimatedTile; }

class oA::AnimatedTile : virtual public Tileset, virtual public Timer
{
public:
    virtual ~AnimatedTile(void) = default;

    AnimatedTile(void) {
        auto &from = append("from") = 0; // Starting animation index (index: y if vertical is true, else x)
        auto &to = append("to") = 0; // Ending animation index (index: y if vertical is true, else x)
        auto &vertical = append("vertical") = false; // If true, will process vertical animation
        get("repeat") = true;
        get("running") = true;
        append("completed"); // Event called on animation completed
        get("triggered").connect([this] { updateTileIndex(); return true; });
        from.connect([this]{ resetTileIndex(); return true; });
        to.connect([this]{ resetTileIndex(); return true; });
        vertical.connect([this]{ resetTileIndex(); return true; });
    }

    virtual String getName(void) const noexcept { return "AnimatedTile"; }

private:
    void resetTileIndex(void) { getIndex() = get("from"); }

    void updateTileIndex(void) {
        auto &index = getIndex();
        if (++index <= get("to"))
            return;
        get("completed").call();
        if (get("repeat"))
            getIndex() = get("from");
    }

    Property &getIndex(void) { return get(get("vertical") ? "yIndex" : "xIndex"); }
};