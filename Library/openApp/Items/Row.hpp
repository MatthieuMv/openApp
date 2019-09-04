/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Row
*/

#pragma once

#include <openApp/Items/Layout.hpp>

namespace oA { class Row; }

class oA::Row : virtual public Layout
{
public:
    virtual ~Row(void) = default;

    virtual String getName(void) const noexcept { return "Row"; }

    virtual void updateLayout(void) override {
        V2f size;
        Float pos = 0.0f;
        bool fill = get("fill");
        if (fill) {
            size.x = getAs<Number>("width") / _children.size();
            size.y = getAs<Number>("height");
        }
        for (auto &child : _children) {
            (child->get("x") = pos).clearTree();
            (child->get("y") = 0).clearTree();
            pos += fill ? size.x : child->getAs<Number>("width");
            if (fill) {
                child->get("width") = size.x;
                child->get("height") = size.y;
            }
        }
    }
};