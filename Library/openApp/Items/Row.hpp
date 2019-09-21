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
        for (auto it = _children.begin(); it != _children.end(); ++it) {
            auto &child = **it;
            if (fill) {
                child.setExpression("width", "(parent.width - (parent.children + 1) * parent.padding) / parent.children");
                child.setExpression("height", "parent.height - parent.padding * 2");
            }
            child.setExpression("y", "parent.padding");
            if (it == _children.begin())
                child.setExpression("x", "parent.padding");
            else {
                auto prev = it - 1;
                child.setExpression("x", (*prev)->getID() + ".x + " + (*prev)->getID() + ".width + parent.padding");
            }
        }
    }
};