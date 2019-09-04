/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Column
*/

#pragma once

#include <openApp/Items/Layout.hpp>

namespace oA { class Column; }

class oA::Column : virtual public Layout
{
public:
    virtual ~Column(void) = default;

    virtual String getName(void) const noexcept { return "Column"; }

    virtual void updateLayout(void) override {
        V2f size;
        Float pos = 0.0f;
        bool fill = get("fill");
        if (fill) {
            size.x = getAs<Number>("width") / _children.size();
            size.y = getAs<Number>("height");
        }
        for (auto &child : _children) {
            child->get("x") = 0;
            child->get("y") = pos;
            pos += fill ? size.y : child->getAs<Number>("width");
            if (fill) {
                child->get("width") = size.x;
                child->get("height") = size.y;
            }
        }
    }
};