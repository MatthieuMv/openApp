/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IndexView
*/

#pragma once

#include <openApp/Items/Item.hpp>
#include <openApp/Core/Log.hpp>

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

    virtual void onAppendChild(Item &item) { Item::onAppendChild(item); updateVisibility(); }

    virtual void onRemoveChild(Item &item) { Item::onAppendChild(item); updateVisibility(); }

private:
    void updateVisibility(void) {
        _children.apply([index = get("index").toInt(), i = 0](auto &child) mutable {
            child->get("visible") = i++ == index;
        });
    }
};