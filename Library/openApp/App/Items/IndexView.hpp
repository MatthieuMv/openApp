/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IndexView
*/

#pragma once

#include <openApp/App/Item.hpp>

namespace oA { class IndexView; }

/**
 * @brief This class is used to render only 1 child, using its 'index' property
 */
class oA::IndexView : virtual public Item
{
public:
    virtual ~IndexView(void) = default;

    IndexView(void) {
        (append("index") = 0).connect([this] { updateVisibility(); return true; });
    }

    String getName(void) const noexcept { return "IndexView"; }

    virtual void onAppendChild(Item &) { updateVisibility(); }

    virtual void onRemoveChild(Item &) { updateVisibility(); }

private:
    void updateVisibility(void) {
        auto index = get("index").toInt();
        auto i = 0;
        for (auto &child : _children) {
            if (i == index)
                child->get("visible") = false;
            else
                child->get("visible") = true;
        }
    }
};