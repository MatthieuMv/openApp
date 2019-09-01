/*
** EPITECH PROJECT, 2019
** TeamfightArena
** File description:
** DropArea
*/

#pragma once

#include <openApp/Items/Item.hpp>
#include <openApp/Core/Log.hpp>

namespace oA { class DropArea; }

class oA::DropArea : virtual public Item
{
public:
    virtual ~DropArea(void) = default;

    DropArea(void) {
        append("droppable") = true; // If true will catch drop events
        append("dropped"); // Event called when something has been dropped and handled
    }

    virtual String getName(void) const noexcept { return "DropArea"; }

    virtual bool onEvent(const Event &event) {
        if (!get("droppable") || event.getType() != Event::Drop)
            return false;
        auto &evt = event.getAs<DropEvent>();
        if (!contains(evt.pos) || evt.target.get() == this || !onCatched(evt))
            return false;
        get("dropped").call();
        return true;
    }

    virtual bool onCatched(const DropEvent &) { return false; }
};