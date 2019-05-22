/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** MenuHandler
*/

#pragma once

// Item
#include "App/Item.hpp"

namespace oA { class MenuHandler; }

class oA::MenuHandler : virtual public Item
{
public:
    MenuHandler(void) {
        auto &idx = append("index"); // Menu index
        idx = 0;
        idx.connect([this] { updateVisibility(); return true; });
    }

    virtual ~MenuHandler(void) {}

    virtual String getName(void) const noexcept { return "MenuHandler"; }

    virtual void onChildAdded(void) { updateVisibility(); }

    void updateVisibility(void) {
        auto i = 0;
        auto target = get("index")->toInt();
        _childs.apply([&i, target](auto &item) {
            item->get("visible") = (i++ == target);
        });
    }
};