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
        bool fill = get("fill"), fillWidth = fill || get("fillWidth"), fillHeight = fill || get("fillHeight");
        bool paddingY = get("paddingY");
        for (auto it = _children.begin(); it != _children.end(); ++it) {
            auto &child = **it;
            if (fillWidth)
                child.setExpression("width", "(parent.width - (parent.children + 1) * parent.paddingX) / parent.children", "Row width");
            if (fillHeight)
                child.setExpression("height", "parent.height - parent.paddingY * 2", "Row height");
            if (paddingY)
                child.setExpression("y", "parent.paddingY", "Row y");
            if (it == _children.begin())
                child.setExpression("x", "parent.paddingX", "Row x");
            else {
                auto prev = it - 1;
                child.setExpression("x", (*prev)->getID() + ".x + " + (*prev)->getID() + ".width + parent.paddingX", "Row x");
            }
        }
    }
};