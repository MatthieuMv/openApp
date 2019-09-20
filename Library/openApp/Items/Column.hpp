/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Column
*/

#pragma once

#include <openApp/Items/Layout.hpp>
#include <openApp/Core/Log.hpp>

namespace oA { class Column; }

class oA::Column : virtual public Layout
{
public:
    virtual ~Column(void) = default;

    virtual String getName(void) const noexcept { return "Column"; }

    virtual void updateLayout(void) override {
        bool fill = get("fill");
        V2f size = { getAs<Number>("width"), getAs<Number>("height") / _children.size() };

        for (auto it = _children.begin(); it != _children.end(); ++it) {
            auto &child = **it;
            if (fill) {
                (child.get("width") = size.x).clearTree();
                (child.get("height") = size.y).clearTree();
            }
            (child.get("x") = 0).clearTree();
            if (it == _children.begin())
                (child.get("y") = 0).clearTree();
            else {
                auto prev = it - 1;
                child.setExpression("y", (*prev)->getID() + ".y + " + (*prev)->getID() + ".height");
            }
        }
    }
};