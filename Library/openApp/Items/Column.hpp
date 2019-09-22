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
        bool fill = get("fill"), fillWidth = fill || get("fillWidth"), fillHeight = fill || get("fillHeight");
        for (auto it = _children.begin(); it != _children.end(); ++it) {
            auto &child = **it;
            if (fillWidth)
                child.setExpression("width", "parent.width - parent.padding * 2");
            if (fillHeight)
                child.setExpression("height", "(parent.height - (parent.children + 1) * parent.padding) / parent.children");
            child.setExpression("x", "parent.padding");
            if (it == _children.begin())
                child.setExpression("y", "parent.padding");
            else {
                auto prev = it - 1;
                child.setExpression("y", (*prev)->getID() + ".y + " + (*prev)->getID() + ".height + parent.padding");
            }
        }
    }
};