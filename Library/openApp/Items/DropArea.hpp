/*
** EPITECH PROJECT, 2019
** TeamfightArena
** File description:
** DropArea
*/

#pragma once

#include <openApp/Items/Item.hpp>

namespace oA { class DropArea; }

class oA::DropArea : virtual public Item
{
public:
    virtual ~DropArea(void) = default;

    DropArea(void) {
        append("droped"); // Event called when something has been dropped and handled
    }

    virtual String getName(void) const noexcept { return "DropArea"; }

    virtual bool onEvent(const Event &event) {
        if (event.getType() != Event::Drop)
            return false;
        auto &evt = event.getAs<DropEvent>();
        if (!contains(evt.pos) || !onCatched(evt.target))
            return false;
        get("droped").call();
        return true;
    }

    virtual bool onCatched(ItemPtr) { return false; }
};