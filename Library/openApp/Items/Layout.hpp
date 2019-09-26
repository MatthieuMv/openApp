/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Layout
*/

#pragma once

#include <openApp/Items/Item.hpp>

namespace oA { class Layout; }

class oA::Layout : virtual public Item
{
public:
    virtual ~Layout(void) = default;

    Layout(void) {
        append("fillWidth") = false;
        append("fillHeight") = false;
        append("fill") = false;
        append("deltaX") = 0.0f;
        append("deltaY") = 0.0f;
        append("padding") = 0;
        append("children") = 0;
        setExpression("paddingX", "padding");
        setExpression("paddingY", "padding");
        get("width").connect([this] { updateLayout(); return true; });
        get("height").connect([this] { updateLayout(); return true; });
    }

    virtual String getName(void) const noexcept { return "Layout"; }

    virtual void onAppendChild(Item &child) override {
        Item::onAppendChild(child);
        get("children") = _children.size();
        updateLayout();
    }

    virtual void onRemoveChild(Item &item) override {
        Item::onRemoveChild(item);
        get("children") = _children.size();
        updateLayout();
    }

    virtual void setChildScreenPos(Item &child) override {
        child.setExpression("screenX", "parent.screenX + parent.deltaX + x");
        child.setExpression("screenY", "parent.screenY + parent.deltaY + y");
    }

    virtual void updateLayout(void) {}
};