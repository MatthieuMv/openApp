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
        append("children") = 0;
        append("fillWidth") = false;
        append("fillHeight") = false;
        append("fill") = false;
        append("padding") = 0;
        append("deltaX") = 0.0f;
        append("deltaY") = 0.0f;
        get("width").connect([this] { updateLayout(); return true; });
        get("height").connect([this] { updateLayout(); return true; });
    }

    virtual String getName(void) const noexcept { return "Layout"; }

    virtual void onAppendChild(Item &child) override {
        Item::onAppendChild(child);
        child.setExpression("screenX", "parent.screenX + parent.deltaX + x");
        child.setExpression("screenY", "parent.screenY + parent.deltaY + y");
        onSizeChanged();
    }

    virtual void onRemoveChild(Item &item) override {
        Item::onRemoveChild(item);
        onSizeChanged();
    }

    virtual void updateLayout(void) {}

private:
    void onSizeChanged(void) {
        get("children") = _children.size();
        updateLayout();
    }
};