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
        bool fill = get("fill");
        V2f size = { getAs<Number>("width") / _children.size(), getAs<Number>("height") };

        for (auto it = _children.begin(); it != _children.end(); ++it) {
            auto &child = **it;
            if (fill) {
                (child.get("width") = size.x).clearTree();
                (child.get("height") = size.y).clearTree();
            }
            (child.get("y") = 0).clearTree();
            if (it == _children.begin()) {
                (child.get("x") = 0).clearTree();
                continue;
            }
            auto prev = it - 1;
            child.setExpression("x", (*prev)->getID() + ".x + " + (*prev)->getID() + ".width");
        }
    }
};